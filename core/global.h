#ifndef GLOBAL_H
#define GLOBAL_H

/** @file */

#define DEEP_COPY_FIELD(T, F) \
    if (other.F) \
    { \
        F = new T(*other.F); \
        F->setParent(this); \
    }

#define DEEP_COPY_COLLECTION(T, F) \
    T* _new##T; \
    for (T* _element : other.F) \
    { \
        _new##T = new T(*_element); \
        _new##T->setParent(this); \
        F << _new##T; \
    }

/**
 * @brief Deletes object and sets the pointer to null.
 *
 * Deletes object under given pointer, but only if the pointer is not null.
 * Also sets the pointer to the null after deleting is done.
 */
#define safe_delete(var) \
    if (var) \
    { \
        delete var; \
        var = nullptr; \
    }

#define qobject_safe_delete(var) \
    if (var) \
    { \
        var->deleteLater(); \
        var = nullptr; \
    }

#define parser_safe_delete(var) delete var

#define static_char static constexpr const char

#define static_qstring(N,V) const static QString N = QStringLiteral(V)

#define DECLARE_SINGLETON(Cls) \
    public: \
        static Cls* getInstance(); \
        static void destroy(); \
    \
    private: \
        static Cls* _instance;

#define DEFINE_SINGLETON(Cls) \
    Cls* Cls::_instance = nullptr; \
    \
    Cls* Cls::getInstance() \
    { \
        if (!_instance) \
            _instance = new Cls(); \
    \
        return _instance; \
    } \
    \
    void Cls::destroy() \
    { \
        safe_delete(_instance); \
    }

#define STRINGIFY(s) _STRINGIFY(s)


#endif // GLOBAL_H
