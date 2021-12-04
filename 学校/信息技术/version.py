import tensorflow as tf

version = tf.__version__
gpu = tf.config.list_physical_devices('GPU')

print(version, '\n', gpu)
