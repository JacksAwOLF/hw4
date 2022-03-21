(1) Your name (and your partner's name if working in a group of two, otherwise clarify you are working alone).

Victor Chen, I am working alone

(2) Your UCSD online username and e-mail used. (If using single sign-on, simply enter your official UCSD email)

v5chen@ucsd.edu

(3) The image-grader URL for full-res images on UCSD online.   

https://raviucsdgroup.s3.amazonaws.com/hw3/9ca4b09e54f4e3d67b55acc80d326b7c/20220316064409/index.html

(4) The platform your code supports and any specific compilation instructions.

MacOS
just run make, and then you can do 
./run (testscene#)
or 
./view (inputfile)

(5) [Optional] Link (URL) to a website which has images and documentation of your raytracer (but please do not post source code publicly on the site).  This website is required if you want extra credit.  Please do not modify it after you submit the assignment.  



(6) Any special comments, issues or points in grading or generally about the assignment you want to convey.  For this assignment, you should at least describe the acceleration structure you use (if you implemented one), and point to any images/documentation/timings showing it works [timings can just be included in the README, ideally images and documentation would go on your website above].  

I made my custom classes, which perhaps was a mistake because it takes me 
around 15 min to compile scene 4 without any acceleration structures.

I then wrote a simple axis aligned bounding box acceleration scheme that
brought it down to 10 minutes, but it really wasn't that big of an
improvement.

If I had more time I would probably utilize OpenGL for the linear algebra.

I have implemented recursive rays, and I am confident that it will work, however I don't have enough time to generate all the images :(