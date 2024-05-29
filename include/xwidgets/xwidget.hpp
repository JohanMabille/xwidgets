/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_WIDGET_HPP
#define XWIDGETS_WIDGET_HPP

#include <optional>
#include <string>
#include <vector>

#include "xlayout.hpp"
#include "xobject.hpp"

namespace xw
{
    /*************************
     * xwidgets declarations *
     *************************/

    template <class D>
    class xwidget : public xobject<D>
    {
    public:

        using base_type = xobject<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<std::string>, derived_type, _dom_classes);
        XPROPERTY(::xw::layout, derived_type, layout);
        XPROPERTY(std::optional<bool>, derived_type, tabbable);
        XPROPERTY(std::optional<std::string>, derived_type, tooltip);

    protected:

        xwidget();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    /***************************
     * xwidgets implementation *
     ***************************/

    template <class D>
    inline xwidget<D>::xwidget()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xwidget<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(_dom_classes(), state["_dom_classes"], buffers);
        xwidgets_serialize(layout(), state["layout"], buffers);
        xwidgets_serialize(tabbable(), state["tabbable"], buffers);
        xwidgets_serialize(tooltip(), state["tooltip"], buffers);
    }

    template <class D>
    inline void xwidget<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(_dom_classes, patch, buffers);
        set_property_from_patch(layout, patch, buffers);
        set_property_from_patch(tabbable, patch, buffers);
        set_property_from_patch(tooltip, patch, buffers);
    }

    template <class D>
    inline void xwidget<D>::set_defaults()
    {
        this->_model_name() = "DOMWidgetModel";
        this->_view_name() = "DOMWidgetView";
    }
}

#endif
