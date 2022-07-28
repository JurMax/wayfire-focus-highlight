#include <wayfire/plugin.hpp>
#include <wayfire/output.hpp>
#include <wayfire/output-layout.hpp>
#include <wayfire/workspace-manager.hpp>
#include "wayfire/view-transform.hpp"
#include <wayfire/signal-definitions.hpp>
#include <fstream>

class focus_highlight_t : public wf::plugin_interface_t
{

    void print_log(std::string message)
    {
        std::ofstream f;
        f.open("/home/jurriaan/documents/programming/wayfire-focus-highlight/log.txt", std::ios_base::app);
        f << message << std::endl;
        f.close();
    }

  public:
    void init() override
    {
        grab_interface->name = "focus_alpha";
        grab_interface->capabilities = wf::CAPABILITY_MANAGE_DESKTOP;

        // output->add_axis(modifier, &axis_cb);

        output->connect_signal("view-focused", &on_focus_changed);
        print_log("init");
    }

    wf::signal_connection_t on_focus_changed = [=] (wf::signal_data_t *data)
    {
        wayfire_view view = wf::get_signaled_view(data);
        print_log("focus");

        set_alpha(view, 0.5);
    };

    void set_alpha(wayfire_view view, float new_alpha)
    {
        wf::view_2D *transformer;
        float alpha;

        if (!view->get_transformer("focus_alpha"))
        {
            view->add_transformer(std::make_unique<wf::view_2D>(view), "focus_alpha");
        }

        transformer =
            dynamic_cast<wf::view_2D*>(view->get_transformer("focus_alpha").get());

        alpha = new_alpha;

        if (alpha > 1.0)
        {
            alpha = 1.0;
        }

        if (alpha == 1.0)
        {
            return view->pop_transformer("focus_alpha");
        }

        if (transformer->alpha != alpha)
        {
            transformer->alpha = alpha;
            view->damage();
        }
    }

    void fini() override
    {
        print_log("fini 0");
        for (wayfire_view& view : wf::get_core().get_all_views())
        {
            print_log("fini 0.5 " + std::to_string((long long unsigned int)&*view));
            if (view != nullptr)
            {

                print_log("fini 1");

                if (!view->get_output() || (view->get_output() == output))
                {
                    print_log("fini 2");
                    if (view->get_transformer("focus_alpha"))
                    {
                        print_log("fini 3");
                        view->pop_transformer("focus_alpha");
                    }
                    print_log("fini 4");
                }
                print_log("fini 5");
            }
            print_log("fini 6");
        }
        print_log("fini done");

        // output->rem_binding(&axis_cb);
    }
};

DECLARE_WAYFIRE_PLUGIN(focus_highlight_t)
