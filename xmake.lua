add_rules("mode.release")

target("probe_driver")
    add_rules("wdk.driver", "wdk.env.wdm")
    add_files("src/probe_driver.cpp")
    set_values("wdk.inf", "probe.inf")

target("probe_client")
    set_kind("binary")
    add_files("src/probe_client.cpp")

target("probe_min")
    add_rules("wdk.driver", "wdk.env.wdm")
    add_files("src/probe_min.cpp")
    set_values("wdk.inf", "probe_min.inf")
