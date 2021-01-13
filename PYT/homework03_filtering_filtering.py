import numpy as np

def apply_filter(image: np.array, kernel: np.array) -> np.array:
    # A given image has to have either 2 (grayscale) or 3 (RGB) dimensions
    assert image.ndim in [2, 3]
    # A given filter has to be 2 dimensional and square
    assert kernel.ndim == 2
    assert kernel.shape[0] == kernel.shape[1]

    kernel_flipped = np.flipud(np.fliplr(kernel))
    dimensions = len(image.shape)
    kernel_shape = kernel_flipped.shape[0]
    res = np.zeros_like(image)
    padding_size = int(np.ceil((kernel_shape - 1) / 2))

    if dimensions == 2:
        image_padded = np.zeros((image.shape[0] + (2 * padding_size), image.shape[1] + (2 * padding_size)))
        image_padded[padding_size:-padding_size, padding_size:-padding_size] = image

    if dimensions == 3:
        image_padded = np.zeros((image.shape[0] + (2 * padding_size), image.shape[1] + (2 * padding_size), image.shape[2]))
        image_padded[padding_size:-padding_size, padding_size:-padding_size, :] = image

    for y in range(image.shape[0]):
        for x in range(image.shape[1]):
            if dimensions == 2:
                 res[y, x] = np.clip((kernel_flipped * image_padded[y:y + kernel_shape, x:x + kernel_shape]).sum(), 0, 255)
            if dimensions == 3:
                for z in range(0, 3):
                    res[y, x, z] = np.clip((kernel_flipped * image_padded[y:y + kernel_shape, x:x + kernel_shape, z]).sum(), 0, 255)

    return res