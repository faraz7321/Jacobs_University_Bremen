import math

import numpy as np
from PIL import Image
from skimage import color, io


def load(image_path):
    """Loads an image from a file path.

    HINT: Look up `skimage.io.imread()` function.

    Args:
        image_path: file path to the image.

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """
    out = None

    ### YOUR CODE HERE
    # Use skimage io.imread

    out = io.imread(fname=image_path)

    ### END YOUR CODE

    # Let's convert the image to be between the correct range.
    out = out.astype(np.float64) / 255
    return out


def dim_image(image):
    """Change the value of every pixel by following

                        x_n = 0.5*x_p^2

    where x_n is the new value and x_p is the original value.

    Args:
        image: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None

    ### YOUR CODE HERE

    image_data = image.copy()
    out = 0.5 * np.sqrt(image_data)

    ### END YOUR CODE

    return out


def convert_to_grey_scale(image):
    """Change image to gray scale.

    HINT: Look at `skimage.color` library to see if there is a function
    there you can use.

    Args:
        image: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width).
    """
    out = None

    ### YOUR CODE HERE
    image_data = image.copy()
    out = color.rgb2gray(image_data)

    ### END YOUR CODE

    return out


def rgb_exclusion(image, channel):
    """Return image **excluding** the rgb channel specified

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "R", "G" or "B".

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None

    ### YOUR CODE HERE

    image_data = image.copy()
    channel_list = ["R", "G", "B"]
    for i in range(3):
        if channel in channel_list:
            pass
        else:
            print("Wrong input: Channel must be R, G or B")
            return image_data

    if channel == "R":
        image_data[:, :, 0] = 0
    elif channel == "G":
        image_data[:, :, 1] = 0
    elif channel == "B":
        image_data[:, :, 2] = 0
    else:
        pass

    out = image_data
    ### END YOUR CODE

    return out


def lab_decomposition(image, channel):
    """Decomposes the image into LAB and only returns the channel specified.

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "L", "A" or "B".

    Returns:
        out: numpy array of shape(image_height, image_width).
    """

    image_data = image.copy()
    lab = color.rgb2lab(image_data)
    out = None

    ### YOUR CODE HERE

    l = lab[:, :, 0]
    a = lab[:, :, 1]
    b = lab[:, :, 2]

    if channel == 'L':
        out = l
    elif channel == 'A':
        out = a
    elif channel == 'B':
        out = b
    else:
        print("Error!")
        return out
    ### END YOUR CODE

    return out


def hsv_decomposition(image, channel="H"):
    """Decomposes the image into HSV and only returns the channel specified.

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "H", "S" or "V".

    Returns:
        out: numpy array of shape(image_height, image_width)
    """

    image_data = image.copy()
    hsv = color.rgb2hsv(image_data)
    out = None

    ### YOUR CODE HERE

    if channel == 'H':
        hsv[:, :, 0] = 0
    elif channel == 'S':
        hsv[:, :, 1] = 0
    elif channel == 'V':
        hsv[:, :, 2] = 0
    else:
        print("Error!")
        return hsv
    out = hsv
    ### END YOUR CODE

    return out


def mix_images(image1, image2, channel1, channel2):
    """Combines image1 and image2 by taking the left half of image1
    and the right half of image2. The final combination also excludes
    channel1 from image1 and channel2 from image2 for each image.

    HINTS: Use `rgb_exclusion()` you implemented earlier as a helper
    function. Also look up `np.concatenate()` to help you combine images.

    Args:
        image1: numpy array of shape(image_height, image_width, 3).
        image2: numpy array of shape(image_height, image_width, 3).
        channel1: str specifying channel used for image1.
        channel2: str specifying channel used for image2.

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None
    ### YOUR CODE HERE
    image1_data = image1.copy()
    image2_data = image2.copy()

    image1_exc = rgb_exclusion(image1_data, channel1)
    image2_exc = rgb_exclusion(image2_data, channel2)

    image1_left = image1_exc[:, :image1.shape[1]//2, :]
    image2_right = image2_exc[:, image2.shape[1]//2:, :]

    out = np.concatenate((image1_left, image2_right), axis=1)

    ### END YOUR CODE

    return out


def mix_quadrants(image):
    """THIS IS AN EXTRA CREDIT FUNCTION.

    This function takes an image, and performs a different operation
    to each of the 4 quadrants of the image. Then it combines the 4
    quadrants back together.

    Here are the 4 operations you should perform on the 4 quadrants:
        Top left quadrant: Remove the 'R' channel using `rgb_exclusion()`.
        Top right quadrant: Dim the quadrant using `dim_image()`.
        Bottom left quadrant: Brighthen the quadrant using the function:
            x_n = x_p^0.5
        Bottom right quadrant: Remove the 'R' channel using `rgb_exclusion()`.

    Args:
        image1: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """
    out = None

    ### YOUR CODE HERE

    image_data = image.copy()
    mid_height, mid_width = image_data.shape[0] // 2, image_data.shape[1] // 2
    
    top_left = np.copy(image_data[:mid_height, :mid_width, :])
    top_right = np.copy(image_data[:mid_height, mid_width:, :])
    bottom_left = np.copy(image_data[mid_height:, :mid_width, :])
    bottom_right = np.copy(image_data[mid_height:, mid_width:, :])
    
    top_left = rgb_exclusion(top_left, 'R')
    top_right = dim_image(top_right)
    bottom_left = np.sqrt(bottom_left)
    bottom_right = rgb_exclusion(bottom_right, 'R')
    
    top = np.concatenate((top_left, top_right), axis=1)
    bottom = np.concatenate((bottom_left, bottom_right), axis=1)
    out = np.concatenate((top, bottom), axis=0)
    
    ### END YOUR CODE

    return out
