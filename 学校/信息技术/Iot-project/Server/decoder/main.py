from pydub import AudioSegment
import numpy as np

a = AudioSegment.from_wav('11981.wav')
a.export('11981_1.wav', format='wav', codec='pcm_u8')
a = AudioSegment.from_wav('11981_1.wav')
# y = np.array(a.get_array_of_samples(), dtype='uint8')
# y = y[3300:123340]
# for i in y:
#     print(i)
a.export('11981_1.raw')
