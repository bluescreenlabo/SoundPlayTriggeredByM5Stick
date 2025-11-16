#define DATASIZE 10

class MovingAve
{
  private:
    float data[DATASIZE];
    int index;
    float sum;

  public:
    MovingAve()
    {
      init();
    }

    void init(float initData = 0.0)
    {
      index = 0;
      sum = 0;
      for (int i=0; i<DATASIZE; i++) {
        data[i] = initData;
        sum += initData;
      }
    }

    float SetData(float set)
    {
      float ret = data[index];
      sum -= ret;
      sum += set;
      data[index] = set;
      index = (index + 1) % DATASIZE;
      return ret;
    }

    float Get(void)
    {
      return (sum / DATASIZE);
    }
};
