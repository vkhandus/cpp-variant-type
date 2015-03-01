#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <memory>
#include <typeinfo>

/*!
 *  \brief Type wrapper utility
 */
template <typename T>
struct TypeWrapper
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

/*!
 *  \brief Type wrapper utility
 */
template <typename T>
struct TypeWrapper<const T>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

/*!
 *  \brief Type wrapper utility
 */
template <typename T>
struct TypeWrapper<const T&>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

/*!
 *  \brief Type wrapper utility
 */
template <typename T>
struct TypeWrapper<T&>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

/*!
 *  \brief Simple variant class
 */
class Variant
{
public:
    Variant()
        : mImpl( new VariantImpl<int>( 0 ) )
    {
    }
            
    Variant( const Variant& other )
        : mImpl( other.mImpl->clone() )
    {
    }

    Variant& operator=( Variant rhs )
    {
        swap( rhs );
        return *this;
    }

    template<class T>
    Variant(T inValue) 
        : mImpl( new VariantImpl<typename TypeWrapper<T>::TYPE>( inValue ) )
    {
    }

    template<class T>
    typename TypeWrapper<T>::REFTYPE value()
    {
        return dynamic_cast<VariantImpl<typename TypeWrapper<T>::TYPE>&>( *mImpl.get() ).m_Value;
    }

    template<class T>
    typename TypeWrapper<T>::CONSTREFTYPE value() const
    {
        return dynamic_cast<VariantImpl<typename TypeWrapper<T>::TYPE>&>( *mImpl.get() ).m_Value;
    }

    template<class T>
    void setValue(typename TypeWrapper<T>::CONSTREFTYPE inValue)
    {
        mImpl.reset( new VariantImpl<typename TypeWrapper<T>::TYPE>( inValue ) );
    }

    bool operator==( const Variant& other ) const
    {
        return mImpl->isEqual( *other.mImpl.get() );
    }

    bool operator!=( const Variant& other ) const
    {
        return !operator==( other );
    }

private:
    void swap( Variant& other ) throw()
    {
        std::auto_ptr< AbstractVariantImpl > temp( mImpl );
        mImpl = other.mImpl;
        other.mImpl = temp;
    }

    struct AbstractVariantImpl
    {
        virtual ~AbstractVariantImpl() {}
        virtual std::auto_ptr<AbstractVariantImpl> clone() = 0;
        
        virtual bool isEqual( const AbstractVariantImpl& other ) = 0;
    };

    template<class T>
    struct VariantImpl : public AbstractVariantImpl
    {
        VariantImpl( T inValue ) 
            : m_Value( inValue ) { }

        ~VariantImpl() {}

        std::auto_ptr<AbstractVariantImpl> clone()
        {                
            return std::auto_ptr<AbstractVariantImpl>( new VariantImpl<T>( m_Value ) );
        }

        virtual bool isEqual( const AbstractVariantImpl& other )
        {
            return typeid( *this ) == typeid( other ) && ( m_Value == ( static_cast<const VariantImpl<T>& >( other ) ).m_Value );
        }

        T m_Value;
    };

    std::auto_ptr< AbstractVariantImpl > mImpl;
};

#endif // __VARIANT_H__
