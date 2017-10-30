#ifndef AUDIOIOBUFFER_H
#define AUDIOIOBUFFER_H

namespace NodeAudio {

  struct AudioIOBuffer {
    float** data;
    AudioIOBuffer(int numChannels, int bufferSize) {
      data = new float *[numChannels];
      for (int i = 0; i < numChannels; i++) {
        data[i] = new float[bufferSize];
      }
    }
    ~AudioIOBuffer() {
      delete [] data;
    }
  };

}
#endif //AUDIOIOBUFFER_H
