#Summarizr
#Stephen Tambussi, Dylan Hoover, Jack Davey, Tanner Kaczmarek, Sabiq Khan
from __future__ import absolute_import
from __future__ import division, print_function, unicode_literals

import tkinter as tk
import time
from tkinter.constants import HORIZONTAL
from tkinter.filedialog import askopenfilename, asksaveasfilename
from sumy.parsers.html import HtmlParser
from sumy.parsers.plaintext import PlaintextParser
from sumy.nlp.tokenizers import Tokenizer
from sumy.summarizers.text_rank import TextRankSummarizer as Summarizer
from sumy.nlp.stemmers import Stemmer
from sumy.utils import get_stop_words

LANGUAGE = "english"
SENTENCES_COUNT = 10

def open_file():
    filepath = askopenfilename(
        filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")]
    )
    if not filepath:
        return
    txt_display.delete("1.0", tk.END)
    with open(filepath, "r") as input_file:
        text = input_file.read()
    window.title(f"Summarizr - {filepath}")
    return text

def save_file():
    filepath = asksaveasfilename(
        defaultextension="txt",
        filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")]
    )
    if not filepath:
        return
    with open(filepath, "w") as output_file:
        text = txt_display.get(1.0, tk.END)
        output_file.write(text)
    window.title(f"Summarizr - {filepath}")

def summarize_html(event):
    #url = "https://en.wikipedia.org/wiki/Automatic_summarization" - test
    url = html_ent.get()

    parser = HtmlParser.from_url(url, Tokenizer(LANGUAGE))
    stemmer = Stemmer(LANGUAGE)
    summarizer = Summarizer(stemmer)
    summarizer.stop_words = get_stop_words(LANGUAGE)

    txt_display.delete("1.0", tk.END) # Clear display before adding to it again
    for sentence in summarizer(parser.document, SENTENCES_COUNT):
        txt_display.insert(tk.END, sentence)

def summarize_text(event):
    # parser = PlaintextParser.from_file("document.txt", Tokenizer(LANGUAGE))
    text = open_file()

    parser = PlaintextParser.from_string(text, Tokenizer(LANGUAGE))
    stemmer = Stemmer(LANGUAGE)
    summarizer = Summarizer(stemmer)
    summarizer.stop_words = get_stop_words(LANGUAGE)

    txt_display.delete("1.0", tk.END)
    for sentence in summarizer(parser.document, SENTENCES_COUNT):
        txt_display.insert(tk.END, sentence)

def change_fontsize(event): #May need to change parameter to scale value
    #print(font_slider.get())
    font_tuple = ("Arial", font_slider.get(), "normal")
    txt_display.configure(font = font_tuple)

if __name__ == "__main__":
    # Basic GUI
    window = tk.Tk()
    window.title("Summarizr")
    
    frm_entry = tk.Frame(master=window)
    html_ent = tk.Entry(master=frm_entry, width=100)
    summarize_btn2 = tk.Button(master=frm_entry, text="Summarize HTML")
    summarize_btn2.bind("<Button-1>", summarize_html)

    text_entry = tk.Frame(master=window)
    summarize_btn1 = tk.Button(master=text_entry, text="Summarize Text")
    summarize_btn1.bind("<Button-1>", summarize_text)

    title_frame = tk.Frame(master=window)
    txt_title = tk.Label(title_frame, text="Summarization Output")
    font_slider = tk.Scale(title_frame, from_=8, to=14, orient=HORIZONTAL, command=change_fontsize, label="Font Size")

    txt_display = tk.Text(window)
    save_btn = tk.Button(window, text="Save Output to File", command=save_file)

    html_ent.grid(row=0, column=0)
    summarize_btn2.grid(row=0, column=1)
    frm_entry.pack()

    summarize_btn1.grid(row=0, column=1)
    text_entry.pack()

    txt_title.grid(row=0, column=0, sticky="S")
    font_slider.grid(row=0, column=1)
    title_frame.pack()

    txt_display.pack()
    save_btn.pack()

    window.mainloop()