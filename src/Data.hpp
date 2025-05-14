#ifndef SGE_DATA_HPP_
#define SGE_DATA_HPP_

#include <initializer_list>
#include <array>
#include <cstddef> 

#include "sge/Logger.hpp"

namespace sge
{

    class IData
    {
    public:
        IData() = default;
        virtual const void* data() const = 0;
        virtual size_t size() const = 0;
        virtual size_t elementSize() const = 0;
        virtual unsigned char countElements() const = 0;
        virtual ~IData() = default;
    };

    template<typename T, size_t N>
    class ElementData : public IData
    {
    public:
        ElementData(std::array<T, N>, unsigned char);
        ElementData(ElementData &&) = default;
        ElementData(const ElementData &) = default;
        ElementData &operator=(ElementData &&) = default;
        ElementData &operator=(const ElementData &) = default;
        ~ElementData() override;
        
        const void* data() const override;
        size_t size() const override;
        size_t elementSize() const override;
        unsigned char countElements() const override;
    private:
        std::array<T, N> m_data;
        unsigned char m_dataItem = 0;
    };


    template<typename T, size_t N>
    ElementData<T, N>::ElementData(std::array<T, N> data, unsigned char count_data_item) : m_data(data), m_dataItem(count_data_item)
    {
        log::debug("ElementData");
    }

    template<typename T, size_t N>
    const void* ElementData<T, N>::data() const
    { 
        return m_data.data();
    }

    template<typename T, size_t N>
    size_t ElementData<T, N>::size() const
    {
        return sizeof(m_data);
    }

    template<typename T, size_t N>
    size_t ElementData<T, N>::elementSize() const
    {
        return sizeof(T);
    }

    template<typename T, size_t N>
    unsigned char ElementData<T, N>::countElements() const
    {
        return m_dataItem;
    }


    template<typename T, size_t N>
    ElementData<T, N>::~ElementData()
    {
        log::debug("~ElementData");
    }

}
#endif
