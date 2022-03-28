import pygame
import zlib
from base64 import b64encode

img = pygame.image.load("Note.bmp")
img_string = pygame.image.tostring(img, 'RGBA')
print(b64encode(zlib.compress(img_string)))
