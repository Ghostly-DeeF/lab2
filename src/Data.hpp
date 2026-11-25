/**
 * @file Data.hpp
 *
 * @author Ghostly-DeeF (moleg200@yandex.ru)
 * @brief Файл содержит описание интерфейса IData и шаблонного класса ElementData
 * @version 0.0.1
 * @date 2026-10-25
 *
 * @copyright Copyright (c) 2026
 *
 * Файл содержит описание интерфейса IData, предназначенного для
 * унифицированного доступа к данным, и шаблонного класса ElementData,
 * реализующего хранение массива элементов фиксированного размера.
 */
#ifndef SGE_DATA_HPP_
#define SGE_DATA_HPP_

#include <initializer_list>
#include <array>
#include <cstddef>

#include "sge/Logger.hpp"

namespace sge
{
    /**
     * @class IData
     * @brief Интерфейс для унифицированного доступа к данным.
     *
     * Определяет набор чистых виртуальных методов, позволяющих получить
     * указатель на данные, их полный размер, размер одного элемента и
     * количество элементов. Наследники реализуют конкретный способ хранения.
     *
     * @note Класс не владеет данными, а предоставляет к ним доступ.
     */
    class IData
    {
    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        IData() = default;

        /**
         * @brief Возвращает указатель на начало данных.
         *
         * @return const void* Указатель на данные.
         */
        virtual const void* data() const = 0;

        /**
         * @brief Возвращает полный размер данных в байтах.
         *
         * @return size_t Полный размер данных в байтах.
         */
        virtual size_t size() const = 0;

        /**
         * @brief Возвращает размер одного элемента в байтах.
         *
         * @return size_t Размер одного элемента в байтах.
         */
        virtual size_t elementSize() const = 0;

        /**
         * @brief Возвращает количество элементов.
         *
         * @return unsigned char Количество элементов.
         */
        virtual unsigned char countElements() const = 0;

        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~IData() = default;
    };

    /**
     * @class ElementData
     * @brief Шаблонный класс хранения массива элементов фиксированного размера.
     *
     * Реализует интерфейс IData для массива std::array<T, N>.
     * Позволяет получить указатель на данные, полный размер массива,
     * размер одного элемента и количество элементов.
     *
     * @tparam T Тип хранимых элементов.
     * @tparam N Максимальный размер массива (количество элементов).
     */
    template<typename T, size_t N>
    class ElementData : public IData
    {
    public:
        /**
         * @brief Конструирует объект ElementData.
         *
         * @param[in] data Массив элементов.
         * @param[in] count_data_item Количество элементов, которые считаются
         *        актуальными (не более N).
         */
        ElementData(std::array<T, N>, unsigned char);

        /**
         * @brief Перемещающий конструктор (по умолчанию).
         */
        ElementData(ElementData &&) = default;

        /**
         * @brief Копирующий конструктор (по умолчанию).
         */
        ElementData(const ElementData &) = default;

        /**
         * @brief Перемещающий оператор присваивания (по умолчанию).
         */
        ElementData &operator=(ElementData &&) = default;

        /**
         * @brief Копирующий оператор присваивания (по умолчанию).
         */
        ElementData &operator=(const ElementData &) = default;

        /**
         * @brief Деструктор.
         */
        ~ElementData() override;

        /**
         * @brief Возвращает указатель на начало данных.
         *
         * @return const void* Указатель на данные.
         */
        const void* data() const override;

        /**
         * @brief Возвращает полный размер массива в байтах.
         *
         * @return size_t Полный размер массива в байтах.
         */
        size_t size() const override;

        /**
         * @brief Возвращает размер одного элемента в байтах.
         *
         * @return size_t Размер одного элемента в байтах.
         */
        size_t elementSize() const override;

        /**
         * @brief Возвращает количество актуальных элементов.
         *
         * @return unsigned char Количество актуальных элементов.
         */
        unsigned char countElements() const override;
    private:
        std::array<T, N> m_data;
        unsigned char m_dataItem = 0;
    };


    template<typename T, size_t N>
    ElementData<T, N>::ElementData(std::array<T, N> data, unsigned char count_data_item) : m_data(data), m_dataItem(count_data_item)
    {
        log::constructor("ElementData");
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
        log::destructor("ElementData");
    }

}
#endif