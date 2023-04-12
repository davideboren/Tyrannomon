#
# Converts Transparent .png spritesheets to 24-bit BMPs
# Any transparent pixels are changed to #FF00FF
#

from PIL import Image
import os
import re

for r, d, f in os.walk("."):
    for dir in d:
        if not os.path.exists(os.path.join("output",dir)):
            os.mkdir(os.path.join("output",dir))
    for file in f:
        if "png" in file:
        
            filepath = os.path.join(r,file)
            output = os.path.join("output",filepath)
            
            print("Converting ",filepath)
            
            spr = Image.open(filepath)
            
            sprW, sprH = spr.size
            for h in range(0,sprH):
                for w in range(0,sprW):
                    if(spr.getpixel((w,h)) == (255,0,255,255)):
                        print("WARNING: Found #FF00FF pixel")
                    if(spr.getpixel((w,h))[3] == 0):
                        spr.putpixel((w,h),(255,0,255,255))
            
            spr = spr.convert("RGB")
            spr.save(re.sub('png','bmp',output))
            