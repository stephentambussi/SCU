package lab8_2;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import javax.swing.border.*;

// This class implements the Observer interface and 
// provides an empty implementation for the interface

class AView extends JPanel implements Observer{
	public void update(Observable o1, Object o2) {};
}
// This is the model class that holds the name and price of an item
// Extends the Observable class; allows addition (and deletion) of observers
// and notifies them when the price changes

class ItemModel extends Observable {
	
	private String itemName;
	private double price;
	
	public ItemModel (String name, double price){
		this.itemName = name; this.price = price;
	}
	public void setPrice(double price){
		// stores the old price before changing the price to the new value
		double oldPrice = this.price;
		this.price = price;
		setChanged();
		// Passes the old price (before change)
		notifyObservers(new Double(oldPrice));
	}
	public double getPrice() {
		return price;
	}
	public String getItemName(){
		return itemName;
	}
	public void increasePrice(double inc){
		setPrice(getPrice()+inc);
	}
	public void decreasePrice(double p){
		setPrice(getPrice()-p);
	}
}
class ItemController implements ActionListener{
	
	private ItemModel itemModel;
	private JFrame appwin;
	private UIView ui;
	private JPanel viewsPanel;
	
	////////An Inner class that provides the text fields and buttons for input///////////////////////////////////////////
	class UIView extends JPanel{
		private JButton incB;
		private JButton reduceB;
		public UIView() {
			setBorder(new TitledBorder("User Interface for Input"));
			
	        JLabel label1 = new JLabel("Item Name");
	        add(label1);
	        
	        JTextField itemIdFld = new JTextField();
	        add(itemIdFld);
	        itemIdFld.setText(itemModel.getItemName());
	       
	        
	        JLabel label2 = new JLabel("Starting Price");
	        add(label2);
	        
	        JTextField itemPriceFld = new JTextField();
	        add(itemPriceFld);
	        itemPriceFld.setText("$"+new Double(itemModel.getPrice()).toString());
	        
	        // Add the buttons
	        incB = new JButton("Increase Price");
	        incB.setActionCommand("inc");
	        add (incB);
	        reduceB = new JButton("Reduce Price");
	        reduceB.setActionCommand("dec");
	        add (reduceB);	     	       
	    }
		 public void addListener(ActionListener listener){
			 incB.addActionListener(listener);
			 reduceB.addActionListener(listener);		 
		 }
	}
	////////////////////////////////////////////////////////////////////////////////////////
	
	public ItemController(ItemModel model){	
		itemModel = model;
		
		// Create the frame to hold  the UI (for input) to the application
		// and output views. The views are restricted to two.
		
		this.appwin = new JFrame("Application Window");	
		ui = new UIView();
		appwin.setLayout(new BorderLayout());
		// Add the UI for input
		appwin.getContentPane().add(ui,BorderLayout.EAST);
		
		// Add a panel to hold upto 2 views.
		viewsPanel = new JPanel();
		viewsPanel.setLayout(new GridLayout(1,2));
		appwin.getContentPane().add(viewsPanel,BorderLayout.WEST);
		appwin. setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	
	}
	public void addAView(AView view){
			viewsPanel.add (view);			
	}
	
	public void actionPerformed(ActionEvent evt){
		// Check where the event is coming from
		// Change the model price
		String cmd = evt.getActionCommand();
		if (cmd.equals("inc")){
			itemModel.increasePrice(1);
		}
		else if (cmd.equals("dec")){
			itemModel.decreasePrice(1);
		}		
	}
	public void activateUI(){
		// Notify the controller when an event (a button click) happens
		ui.addListener(this);
		
		 //Display the window.
		appwin.setSize(300,300);
		appwin.setLocationRelativeTo(null);
        appwin.pack();
        appwin.setVisible(true);		
	}	
	public void startApp(){
		activateUI();	
	}
}
////////////////////////////////Output View 1///////////////////////////////////
class DisplayView extends AView {	
	private JLabel label ;
	public DisplayView (){
		setBackground(Color.CYAN);
		TitledBorder border = new TitledBorder("View With Colors");
		border.setTitleColor(Color.WHITE);
		setBorder(border);
		
	    label = new JLabel("", SwingConstants.CENTER);
	    label.setForeground(Color.WHITE);
	    label.setFont(new Font("Serif", Font.PLAIN, 20));
		setLayout(new BorderLayout());
		add(label,BorderLayout.CENTER);		
	}	
	// This method is called when the Observable model is changed
	public void update(Observable o1, Object price){
		ItemModel model = (ItemModel) o1;
		double oldPrice = ((Double)price).doubleValue();
		if (model.getPrice() < oldPrice){
			setBackground(Color.RED);		
		}
		else{
			setBackground(Color.BLUE);
					
		}
		label.setText(new Double(model.getPrice()).toString());
	}
}
////////////////////////////////Output View 2///////////////////////////////////
class TextView extends AView {	
	private JTextArea area ;
	JScrollPane scrollPane;
	public TextView (){			
		//
		setBorder(new TitledBorder("A text view"));
	    area = new JTextArea("",2,20);
		area.setBackground(Color.BLACK);
		area.setForeground(Color.WHITE);
	    area.setLineWrap(true);
	    area.setEditable(false);
	    area.setFont(new Font("Serif", Font.ITALIC, 16));
	    area.setWrapStyleWord(true);
	    add(area,BorderLayout.CENTER);
	}
	// This method is called when the Observable model is changed
	public void update(Observable o1, Object price){
		ItemModel model = (ItemModel) o1;
		double oldPrice = ((Double)price).doubleValue();
		String s = "";
		double currentPrice = model.getPrice();	
		s = "Old Price: $" +oldPrice +"\nCurrent Price: $"+ currentPrice +"\n";		
		area.setText(s);
	}
}
public class MVCDemo {
	public static void main(String[] args) {
		
			// Create a Model
			ItemModel model = new ItemModel(" Craft Vase",11.00);
			
			// Create View 1
			DisplayView display = new DisplayView();
			// Add the View as the Observer on the model
			model.addObserver(display);
			
			// Create View 2
			TextView textView = new TextView();
			// Add the View as the Observer on the model
			model.addObserver(textView);	
			
			// Create a Controller and connect it with the model
			ItemController controller = new ItemController(model);
			
			// Add the views to the controller so that it displays them
			// in a window
			controller.addAView(display);
			controller.addAView(textView);
			
			// Start the application now
			controller.startApp();

	}

}
