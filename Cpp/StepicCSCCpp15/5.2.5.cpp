#include <cstddef> // size_t
#include <cstring>
#include <utility>
#include <iostream>

/*struct From
{
    From(int value = -1) : value_(new int(value)) {}
    From(From const &from) : value_(new int(*from.value_)) {}
    ~From()
    {
        delete value_;
    }

    int *value_;

};

*/

struct ChunkString; //Добавляем для видимоси

struct String_
{

    struct ProxyString
    {
        ProxyString(const char *str = "", size_t from = 0)
            : size_(strlen(str))
            , str_(new char[size_+1])
            , from_(from)
        {
            strcpy(str_, str);
        }

        String_ operator[](size_t to) const
        {
            char *tmp = new char[to - from_ + 1]();
            memcpy(tmp, str_ + from_, to - from_);

            String_ tmp_str(tmp);
            delete [] tmp;
            return tmp_str;
        }

        ~ProxyString()
        {
            size_ = 0;
            delete [] str_;
        }

        size_t size_;
        size_t from_;
        char *str_;
    };

    String_(const char *str = "")
    {
        size_ = strlen(str);
        str_ = new char[size_+1];
        strcpy(str_, str);
    }

    String_(size_t n, char c)
    {
        str_ = new char[n+1];
        memset(str_,c,n);
        str_[n] = 0;
    }

    String_ &operator=(const String_ &str) {
        if(this != &str)
            String_(str).swap(*this);
        return *this;
    }

    void swap(String_ &str)
    {
        std::swap(size_, str.size_);
        std::swap(str_, str.str_);
    }

   /* String_(const String_ &str):size_(str.size()), str_(new char[size_+1]), from(str.from)
    {
        memcpy(str_, str.c_str(), size_+1);
    }*/

    String_(const String_ &str):size_(str.size()), str_(new char[size_+1])
    {
        memcpy(str_, str.c_str(), size_+1);
    }

    size_t size()
    {
        return size_;
    }

    size_t size() const
    {
        return size_;
    }

    char &at(size_t idx)
    {
        return str_[idx];
    }


    char at(size_t idx) const
    {
        return str_[idx];
    }

    const char *c_str()
    {
        return str_;
    }

    const char *c_str() const
    {
        return (char const *)str_;
    }

    int compare(String_ &str)
    {
        return strcmp(str_,str.c_str());
    }

    void append(String_ &str) {
        char *tmp_str_ = new char[size_ + str.size() +1];
        memcpy(tmp_str_, str_, size_);
        memcpy(tmp_str_+size_, str.c_str(), str.size());
        delete [] str_;
        str_ = tmp_str_;
        size_ +=  str.size();
        str_[size_] = 0;
    }

    ~String_()
    {
        size_ = 0;
        delete [] str_;
    }


    //Это решение не завершено, и к тому же оно требует переопределение конструктора,
    //что по условию задачи врятли поощряется
    /*String_ operator[](int from_to) const
  {
      if(*from.value_ == -1)
      {
          *from.value_ = from_to;
          return *this;
      }
      else
      {
          char *tmp = new char[from_to - *from.value_ + 1]();
          memcpy(tmp, str_ + *from.value_, from_to - *from.value_);

          String_ tmp_str(tmp);
          delete [] tmp;
          return tmp_str;
      }
  }*/

    //Это решение прошло контест на Stepic
    /*ProxyString operator[](size_t from) const
    {
        return (ProxyString(this->str_, from));
    }*/

    //Это решение не работает, так как type 'struct ChunkString' is incomplete
    /*ChunkString operator[](size_t from) const
    {
        return ChunkString(str_, from);
    }*/

    size_t size_;
    char *str_;
    //From from;
};

struct ChunkString : public  String_
{
    ChunkString (String_ const &str, size_t from) : String_(str), from_(from) {}

    String_ operator[](size_t to) const
    {
        char tmp[to - from_ + 1];
        memcpy(tmp, str_ + from_, to - from_);
        tmp[to-from_] = 0;
        return String_(tmp);
    }

    size_t from_;
};

int _5_2_5()
{

    //String_ const hello("hello");
    //String_ const hell = hello[0][4];
    //String_ const ell  = hello[1][4];

    //std::cout << hello.str_ << std::endl;
    //std::cout << hell.str_ << std::endl;
    //std::cout << ell.str_ << std::endl;
    /*std::cout << *From(6).value_<< std::endl;
    std::cout << *From(From(7)).value_<< std::endl;

    String_ tmp("tmp");
    *tmp.from.value_ = 6;
    std::cout << *String_(tmp).from.value_ << std::endl;
    std::cout << *From(tmp.from).value_ << std::endl;*/





    return 0;
}
