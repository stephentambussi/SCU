#Stephen Tambussi
#Program displays face in point or triangle rendering modes and rotates around the y-axis 
import tkinter as tk
import math
import csv
wireframe = 1 # 0 = point only rendering | 1 = triangle(wireframe) rendering
#Higher framerate with point only rendering
counter = 0
class Engine_3d:
    def __init__(self, points, triangles, height=600, width=600, distance=3, scale=500): #initialization function of class 
        self.window = tk.Tk()
        self.window.title('COEN148 Assignment 2')
        self.image = tk.Canvas(self.window, width=width, height=height)
        self.image.pack()
        self.height = height
        self.width = width
        self.distance = distance
        self.scale = scale
        self.points = points
        self.triangles = triangles
        self.shapes = []
    def projectPoint(self, point):
        #projects the 3d points onto the 2d view plane
        (x, y, z) = (point[0], point[1], point[2])
        projY = int(self.height / 2 + ((y * self.distance) / (z + self.distance)) * self.scale)
        projX = int(self.width / 2 + ((x * self.distance) / (z + self.distance)) * self.scale)
        return (projX, projY)
    def rotate(self, axis, angle, point):
        #rotate point around axis
        (x, y, z) = (point[0], point[1], point[2])
        angle = angle / 450 * 180 / math.pi
        sqrt2 = math.sqrt(2)
        if axis == 'z':
            #rotate aroud Z axis
            newX = x * math.cos(angle) - y * math.sin(angle)
            newY = y * math.cos(angle) + x * math.sin(angle)
            newZ = z
        elif axis == 'x':
            #rotate around X axis
            newY = y * math.cos(angle) - z * math.sin(angle)
            newZ = z * math.cos(angle) + y * math.sin(angle)
            newX = x
        elif axis == 'y':
            #rotate around Y axis
            newX = x * math.cos(angle) - z * math.sin(angle)
            newZ = z * math.cos(angle) + x * math.sin(angle)
            newY = y
        else:
            raise ValueError('invalid rotation axis')
        x = newX
        y = newY
        z = newZ
        return (x, y, z)
    def clear(self):
        self.image.delete('all')
    def drawTriangle(self, points): #for wireframe drawing
        a, b, c = points[0], points[1], points[2]
        coords = [a[0], a[1], b[0], b[1], c[0], c[1]]
        self.shapes.append(self.image.create_polygon(coords, fill="", outline="red"))
    def drawPoint(self, point_x, point_y): #for point only drawing
        self.image.create_line(point_x, point_y, point_x+1, point_y, fill="red")
    def render(self):
        global counter
        coords = []
        for point in self.points:
            coords.append(self.projectPoint(self.rotate('y', counter, self.rotate('x', 270, point))))
            #call x rotate so it faces right way first, then call rotate with counter so it spins around as program runs
        for coord in coords:
            self.drawPoint(coord[0], coord[1])
        if(wireframe == 1):
            for triangle in self.triangles:
                self.drawTriangle((coords[triangle[0]], coords[triangle[1]], coords[triangle[2]]))
        self.image.update()
points = []
#with open('face-vertices.data') as csv_file:
with open('C:/Users/steve/Desktop/COEN148/HW2/face-vertices.data') as csv_file: #needed absolute path for VS code
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:    
        points.append((float(row[0]), float(row[1]), float(row[2])))

triangles = []
#with open('face-index.txt') as csv_file: 
with open('C:/Users/steve/Desktop/COEN148/HW2/face-index.txt') as csv_file: #needed absolute path for VS code
    csv_reader = csv.reader(csv_file, delimiter=',')
    for index in csv_reader:
        triangles.append((int(index[0]), int(index[1]), int(index[2])))
test = Engine_3d(points, triangles) #creates class object to actually run program
while True:
    test.clear() #Clears screen to prepare for next frame
    test.render() #Does the actual rendering
    counter = counter + 0.5 #increments counter variable to rotate 

