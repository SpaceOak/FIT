"""
Filtering image according to input matrix
Expected to be used by calling apply conv foo at the end of file
"""
import numpy as np


def get_data(image: np.array, kernel: np.array, location: []):
    """
    Extracting data from RGB image
    ( returning matrix of relative
    pixels by channel according
    to kernel size )
    :param image:
    Image to be extracted from
    :param kernel:
    Kernel to calculate size of data to be extracted
    :param location:
    i, j, q: X position, Y position, channel index
    """
    ran = len(kernel)
    bounds = int((ran - 1) / 2)
    matrix = []

    for i in range(ran):
        row = []
        for j in range(ran):
            if location[0] - bounds + i < 0 or \
                    location[0] - bounds + i > len(image) - 1 or \
                    location[1] - bounds + j > len(image[0]) - 1 or \
                    location[1] - bounds + j < 0:
                row.append(0)
            else:
                row.append(image[location[0] - bounds + i]
                                [location[1] - bounds + j]
                                [location[2]])
        matrix.append(row)

    return matrix


def get_data_grayscale(image: np.array, kernel: np.array, location: []):
    """
    Extracting data from grayscale image
    ( returning matrix of relative
    pixels by channel according
    to kernel size )
    :param image:
    Image to be extracted from
    :param kernel:
    Kernel to calculate size of data to be extracted
    :param location:
    i, j: X position, Y position
    """
    ran = len(kernel)
    bounds = int((ran - 1) / 2)
    matrix = []

    for i in range(ran):
        row = []
        for j in range(ran):
            if location[0] - bounds + i < 0 or \
                    location[0] - bounds + i > len(image) - 1 or \
                    location[1] - bounds + j > len(image[0]) - 1 or \
                    location[1] - bounds + j < 0:
                row.append(0)
            else:
                row.append(image[location[0] - bounds + i]
                                [location[1] - bounds + j])
        matrix.append(row)

    return matrix


def convolve(img: np.array, kernel: np.array) -> np.array:
    """
    Solution for RGB image
    :param img:
    image to be convolved
    :param kernel:
    kernel to be used to convolve image
    """
    # 2D array of zeros
    res = np.zeros(shape=(len(img), len(img[0]),
                          len(img[0][0])), dtype=np.uint8)

    # Iterate over the rows
    for i, _ in enumerate(img):
        # Iterate over the columns
        for j, _ in enumerate(img[i]):
            # Iterate over the channels
            for q, _ in enumerate(img[i][j]):
                tmp = get_data(img, kernel, [i, j, q])
                a = int(0)
                for row, elem in enumerate(tmp):
                    for col, data in enumerate(elem):
                        a += data * kernel[row][col]

                res[i][j][q] = min(255, max(0, a))

    return res


def grayscale_convolve(img: np.array, kernel: np.array) -> np.array:
    """
    Solution for grayscale images
    :param img:
    image to be convolved
    :param kernel:
    kernel to be used to convolve image
    """
    # 2D array of zeros
    res = np.zeros(shape=(len(img), len(img[0])), dtype=np.uint8)

    # Iterate over the rows
    for i, _ in enumerate(img):
        # Iterate over the columns
        for j, _ in enumerate(img[i]):
            tmp = get_data_grayscale(img, kernel, [i, j])
            a = int(0)

            for row, _ in enumerate(tmp):
                for col, _ in enumerate(tmp[row]):
                    a += tmp[row][col] * kernel[row][col]

                res[i][j] = min(255, max(0, a))
    return res


def apply_filter(image: np.array, kernel: np.array) -> np.array:
    """
    Main foo solving basic cases, deciding which method to be called
    :param image:
    image to be convolved
    :param kernel:
    kernel to be used to convolve image
    """
    # A given image has to have either 2 (grayscale) or 3 (RGB) dimensions
    assert image.ndim in [2, 3]
    # A given filter has to be 2 dimensional and square
    assert kernel.ndim == 2
    assert kernel.shape[0] == kernel.shape[1]

    if kernel.shape[0] == 2:
        a = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        a[0][0] = kernel[0][0]
        a[0][1] = kernel[0][1]
        a[1][0] = kernel[1][0]
        a[1][1] = kernel[1][1]
        kernel = a

    if image.ndim == 3:
        return convolve(image, kernel)

    return grayscale_convolve(image, kernel)
