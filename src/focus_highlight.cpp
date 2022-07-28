#include <wayfire/plugin.hpp>
#include <wayfire/output.hpp>
#include <wayfire/output-layout.hpp>
#include <wayfire/workspace-manager.hpp>

class focus_highlight_t : public wf::plugin_interface_t
{
    wf::option_wrapper_t<wf::activatorbinding_t> workspace_keys =
        {"focus_highlight/test"};

public:
    void init() override
    {
    }

    void fini() override
    {
    }
};

DECLARE_WAYFIRE_PLUGIN(focus_highlight_t)
