#ifndef ADS_UTIL_FUNCTION_VALUE_FUNCTION_VALUE_1D_HPP_
#define ADS_UTIL_FUNCTION_VALUE_FUNCTION_VALUE_1D_HPP_


namespace ads {

struct function_value_1d {
    double val;
    double dx;

    function_value_1d(double val, double dx)
    : val{ val }
    , dx{ dx }
    { }

    function_value_1d(): function_value_1d{ 0, 0 }
    { }

    function_value_1d& operator += (const function_value_1d& v) {
        val += v.val;
        dx  += v.dx;
        return *this;
    }

    function_value_1d& operator -= (const function_value_1d& v) {
        val -= v.val;
        dx  -= v.dx;
        return *this;
    }

    function_value_1d operator - () const {
        return { -val, -dx };
    }

    function_value_1d& operator *= (double a) {
        val *= a;
        dx  *= a;
        return *this;
    }

    function_value_1d& operator /= (double a) {
        val /= a;
        dx  /= a;
        return *this;
    }
};

inline function_value_1d operator + (function_value_1d x, const function_value_1d& v) {
    x += v;
    return x;
}

inline function_value_1d operator - (function_value_1d x, const function_value_1d& v) {
    x -= v;
    return x;
}

inline function_value_1d operator * (double a, function_value_1d u) {
    u *= a;
    return u;
}

inline function_value_1d operator * (function_value_1d u, double a) {
    u *= a;
    return u;
}

inline function_value_1d operator / (function_value_1d u, double a) {
    u /= a;
    return u;
}

}


#endif /* ADS_UTIL_FUNCTION_VALUE_FUNCTION_VALUE_1D_HPP_ */
