import math
from PIL import Image 
pixels_x = 640
pixels_y = 480
img = Image.new('RGB',(pixels_x, pixels_y))
pixels = img.load()
###########################
#Step 1 - Draw Empty Circle
#Bresenham's Algorithm
###########################
xp = int(pixels_x / 2) #x positioning of the circle
yp = int(pixels_y / 2) #y positioning of the circle
def draw_circle(x, y): #Repeat pixels call 8 times to draw full circle
    pixels[xp+x,yp+y] = (0, 0, 255)
    pixels[xp-x,yp+y] = (0, 0, 255)
    pixels[xp+x,yp-y] = (0, 0, 255)
    pixels[xp-x,yp-y] = (0, 0, 255)
    pixels[xp+y,yp+x] = (0, 0, 255)
    pixels[xp-y,yp+x] = (0, 0, 255)
    pixels[xp+y,yp-x] = (0, 0, 255)
    pixels[xp-y,yp-x] = (0, 0, 255)
rad = 180 #change this to change circle size
x = 0
y = rad
d = (5/4) - rad
draw_circle(x, y)
while y>=x:
    x = x + 1
    if d > 0: #Chooses southeast direction
        y = y - 1
        d = d + 2 * (x-y) + 5
    else: #Chooses east direction
        d = d + 2 * x + 3 
    draw_circle(x, y)
##########################
#Step 2 - Fill Circle
#Scanline algorithm
##########################
#Top down and fills as it goes
def Line(x_1, y_1, x_2, y_2):
    x1 = x_1
    y1 = y_1
    x2 = x_2
    y2 = y_2
    if x_1 > x_2:
        x1 = x_2
        y1 = y_2
        x2 = x_1
        y2 = y_1
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    inc_dec = 0
    if y2 >= y1: #y increasing
        inc_dec = 1
    else: #y decreasing
        inc_dec = -1
    if dx > dy: 
        two_dy = (2*dy)
        two_dy_dx = (2*(dy-dx))
        p = ((2*dy)-dx)
        x=x1
        y=y1
        pixels[x, y] = (0, 0, 255)
        while x < x2: #fills between intersections
            x = x + 1
            if p < 0:
                p = p + two_dy
            else:
                y = y + inc_dec
                p = p + two_dy_dx
            pixels[x, y] = (0, 0, 255)
    else:
        two_dx = (2*dx)
        two_dx_dy = (2*(dx-dy))
        p = ((2*dx)-dy)
        x = x1
        y = y1
        pixels[x, y] = (0, 0, 255)
        while y != y2:
            y = y + inc_dec
            if p < 0:
                p = p + two_dx
            else:
                x = x + 1
                p = p + two_dx_dy
            pixels[x, y] = (0, 0, 255)

x1 = 0
x2 = 0
counter = yp + rad
for i in range(yp - rad, counter):
    x1 = xp + math.sqrt((rad*rad)-((i-yp)*(i-yp))) + 0.5
    x2 = xp - math.sqrt((rad*rad)-((i-yp)*(i-yp))) + 0.5
    Line(x1, i, x2, i)
##########################
#Step 3 - Anti-aliasing
#Supersampling
##########################
#Doubles image resolution and then scales back down
scaled = img.resize((320, 240))
scaled.show()