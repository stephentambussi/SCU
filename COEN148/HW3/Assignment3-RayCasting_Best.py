#Stephen Tambussi - Assignment 3
import numpy as np
from PIL import Image

class sphere(object):
    def __init__(self, center, radius, ambient, diffuse, specular, shininess, reflection):
        self.c = center
        self.r = radius
        self.a = ambient
        self.df = diffuse
        self.spec = specular
        self.sh = shininess
        self.reflect = reflection
    def intersect(self, ray_origin, ray_direction):
        #Calculates point of intersection between ray and sphere object
        b = 2 * np.dot(ray_direction, ray_origin - self.c)
        c = np.linalg.norm(ray_origin - self.c)**2 - self.r**2
        delta = b**2 - 4 * c
        if delta > 0:
            t1 = (-b + np.sqrt(delta)) / 2
            t2 = (-b - np.sqrt(delta)) / 2
            if t1 > 0 and t2 > 0:
                return min(t1, t2)
        return None

class light(object):
    def __init__(self, position, ambient, diffuse, specular):
        self.p = position
        self.a = ambient
        self.df = diffuse
        self.spec = specular
    def compute_light(self, near_object, intersection, intersection_to_light, camera, normal_to_surface):
        #Computes color with lighting
        #RGB array initialized to zero
        illumination = np.zeros((3))
        #ambient color calculation
        illumination += near_object.a * self.a
        #diffuse color calculation
        illumination += near_object.df * self.df * np.dot(intersection_to_light, normal_to_surface)
        #specular color calculation
        intersection_to_camera = normalize(camera - intersection)
        H = normalize(intersection_to_light + intersection_to_camera)
        illumination += near_object.spec * self.spec * np.dot(normal_to_surface, H)**(near_object.sh / 4)
        return illumination

def normalize(vector):
    return vector / np.linalg.norm(vector)

def reflected(vector, axis):
    return vector - 2 * np.dot(vector, axis) * axis

def scale_to_rgb(color):
    #converts the 0-1 scale to 0-255
    return (int(color[0] * 255), int(color[1] * 255), int(color[2] * 255))

def nearest_intersected_object(objects, ray_origin, ray_direction):
    #finds nearest object that ray intersects
    distances = []
    for obj in objects:
        distances.append(obj.intersect(ray_origin, ray_direction))
    nearest_object = None
    min_distance = np.inf
    for index, distance in enumerate(distances):
        if distance and distance < min_distance:
            min_distance = distance
            nearest_object = objects[index]
    return nearest_object, min_distance

pixels_x = 320
pixels_y = 240
max_depth = 3
img = Image.new('RGB', (pixels_x, pixels_y))

camera = np.array([0, 0, 1]) #eye position
ratio = float(pixels_x) / pixels_y #aspect ratio
screen = (-1, 1 / ratio, 1, -1 / ratio) #(left, top, right, bottom) - view plane coordinates

objs = [] #list to hold sphere objects
lights = [] #list to hold light objects
objs.append(sphere(np.array([-0.2, 0, -1]), 0.7, np.array([0.1, 0, 0]), np.array([0.7, 0, 0]), np.array([1, 1, 1]), 100, 0.5)) #append large red sphere
objs.append(sphere(np.array([0.1, -0.3, 0]), 0.1, np.array([0.1, 0, 0.1]), np.array([0.7, 0, 0.7]), np.array([1, 1, 1]), 100, 0.5)) #append small purple shere
objs.append(sphere(np.array([-0.1, 0.3, 0]), 0.15, np.array([0, 0.1, 0]), np.array([0, 0.6, 0]), np.array([1, 1, 1]), 100, 0)) #append medium green sphere
objs.append(sphere(np.array([0, -9000, 0]), 9000 - 0.7, np.array([0.1, 0.1, 0.1]), np.array([0.6, 0.6, 0.6]), np.array([1, 1, 1]), 100, 0)) #append ground "plane"
lights.append(light(np.array([5, 5, 5]), np.array([1, 1, 1]), np.array([1, 1, 1]), np.array([1, 1, 1])))
#main loop
for i, y in enumerate(np.linspace(screen[1], screen[3], pixels_y)):
    for j, x in enumerate(np.linspace(screen[0], screen[2], pixels_x)):
        #computation of ray - put into function
        pixel = np.array([x, y, 0]) #pixel lies on screen plane
        origin = camera #ray origin
        direction = normalize(pixel - origin) #direction of ray
        
        l = lights[0]
        #reflection calculation
        color = np.zeros((3))
        reflection = 1
        for k in range(max_depth):
            #intersection check
            nearest_object, min_distance = nearest_intersected_object(objs, origin, direction)
            if nearest_object is None:
                break

            #calculate intersection point between ray and nearest object
            intersection = origin + min_distance * direction

            #light intersection calculation
            normal_to_surface = normalize(intersection - nearest_object.c)
            shifted_point = intersection + 1e-5 * normal_to_surface
            intersection_to_light = normalize(l.p - shifted_point)

            _, min_distance = nearest_intersected_object(objs, shifted_point, intersection_to_light)
            intersection_to_light_distance = np.linalg.norm(l.p - intersection)
            is_shadowed = min_distance < intersection_to_light_distance
            if is_shadowed:
                break
                
            #reflection calculation
            color += reflection * l.compute_light(nearest_object, intersection, intersection_to_light, camera, normal_to_surface)
            reflection *= nearest_object.reflect
                
            origin = shifted_point
            direction = reflected(direction, normal_to_surface)

        img.putpixel((j, i), scale_to_rgb(np.clip(color, 0, 1)))
    print("progress: %d/%d" % (i+1, pixels_y))
img.show() #show final image
