
#ifndef __H_VALUE
#define __H_VALUE


#define _M_bool_val(value)    ((Value){ VAL_BOOL,   {.boolean = value} })
#define _M_num_val(value)     ((Value){ VAL_NUMBER, {.number = value}  })
#define _M_nil_val            ((Value){ VAL_NIL,    {.number = 0}      })

#define _M_val_as_bool(value) ((value).as.boolean)
#define _M_val_as_num(value)  ((value).as.number)

#define _M_is_val_bool(value) ((value).type == VAL_BOOL)
#define _M_is_val_num(value)  ((value).type == VAL_NUMBER)

#define _M_bool_to_num(value) ((_M_val_as_bool(value) == true) ? 1.0 : 0.0)
#define _M_bool_string(value) ((value).as.boolean ? "true" : "false")

#define _M_force_num(value)   (_M_is_val_num(value)  ? _M_val_as_num(value) : _M_bool_to_num(value))


typedef enum{

    VAL_BOOL,
    VAL_NUMBER,
    VAL_NIL

} ValueType;


typedef struct {

    ValueType type;

    union{

        bool boolean;
        double number;
    } as;
} Value;




#endif