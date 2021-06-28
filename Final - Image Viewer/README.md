## About the project

This is my final project for [Harvard CS50x 2020](https://cs50.harvard.edu/x/2020/) course.
My project is a simple image viewer made with python 3 and it's GUI library Tkinter.
It opens images from current directory, resizes it to fit a window with doing some math and shows it on a screen.
GUI also has navigation buttons to navigate through images in current directory.



## Description
  Image viewer runs on tkinter GUI library. When program is executed, it opens 800x600 window, then scans for images in current directory, saves filenames in a list called images. Then it opens first photo by name found in a created list and determines it's dimensions with PIL library. If photo does not fit program window (800x560 area of window is for showing an image) it does some math to resize it without it's messing current ratio.
  GUI also has buttons (back "<<" and forward ">>") to navigate through images.


## technical details
  Image viewer uses OS library for scanning image files in current directory, then saves it into a list.
  GUI window is built with Tkinter and first image is opened fromn a name list. Then, image is resized a few times if needed to match
  window area without losing image ratio. Image is displayed and user views it. Navigation button is enabled to move forward and back.
  If there are no images, error message is displayed

## Image resize process

```
resizes image to fit app window if it overflows
frame app window space for image:

  width(800)
  ----------
  |        | height(560)
  |        |
  ----------

  **Case 1 image (image fits window space):

  original_width <= 800
      -----
      |   | original_height <= 560
      -----
  image is directly returned by function,
  bacause it fits image space in app window

  **Case 2 only image width overflows image space in window

  original_width > 800
  ------------------
  |                | original_height <= 560
  |                |
  ------------------

  **Case 3 only image height overflows image space in window

  original_width <= 800
  -------
  |     |
  |     |
  |     | original_height > 560
  |     |
  -------

  **Case 4 both height and width overflows image space in window

  original_width > 800
  ------------------
  |                |
  |                |  original_height > 560
  |                |
  |                |
  ------------------

  In each case, x and y is resized with ratio to not mess an image
 ```


## How to use

How to run Image Viewer

```
$ python3 image_viewer.py
```

## Requirements

- python 3
- Tkinter library
- PIL library (ImageTK and image)

This is CS50 :)
