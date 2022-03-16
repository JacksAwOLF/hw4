(1) Your name (and your partner's name if working in a group of two, otherwise clarify you are working alone).

Victor Chen, I am working alone

(2) Your UCSD online username and e-mail used. (If using single sign-on, simply enter your official UCSD email)

v5chen@ucsd.edu

(3) Documentation of result images for scene1.test and scene2.test.  Include images of your raytracer generating these images for each of the three camera positions given (and ideally compare to the OpenGL version provided).  You can simply include these images in a prominent place in your zip and point to them in the README, although fancier solutions like a simple html or PDF file with the images included would also be appreciated.


(4) [Optional but encouraged] The image-grader URL for full-res images on UCSD online.   This is optional for the milestone, but you are highly encouraged to demonstrate at least some of the images on UCSD Online.

(5) The platform your code supports and any specific compilation instructions.

Wrote on macOS
just run make, then ./view inputFile

(6) [Optional] Any special comments, issues or points in grading or generally about the assignment you want to convey.

I made my custom classes, which perhaps was a mistake because it takes me 
around 10 min to compile scene 4 without any acceleration structures.

I then wrote a simple axis aligned bounding box acceleration scheme that
brought it down to ... minutes, but it really wasn't that big of an
improvement.

If I had more time I would probably utilize OpenGL for the linear algebra.