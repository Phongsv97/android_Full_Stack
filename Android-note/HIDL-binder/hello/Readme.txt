1. mkdir hello/1.0 directory in hardware/interface.
2. create IHello.hal
3. create Android.bp in 1.0 folder
3. make default folder in 1.0 folder.
4. run command:
  - hidl-gen -o hardware/interfaces/hello/1.0/default/ -Lc++-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport android.hardware.hello@1.0
to create .cpp and .h file

  - hidl-gen -o hardware/interfaces/hello/1.0/default/ -Landroidbp-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport android.hardware.hello@1.0
to create Android.bp file

5. modify .cpp and .h file to map with driver.

note: add following line in device.mk
PRODUCT_PACKAGES += android.hardware.hello@1.0-service # for service
ODUCT_PACKAGES += test_hello				# for test file

modify default/Android.bp

cc_binary {								--> change to cc_binary (because this is binder method)
    // FIXME: this should only be -impl for a passthrough hal.
    // In most cases, to convert this to a binderized implementation, you should:
    // - change '-impl' to '-service' here and make it a cc_binary instead of a
    //   cc_library_shared.
    // - add a *.rc file for this module.
    // - delete HIDL_FETCH_I* functions.
    // - call configureRpcThreadpool and registerAsService on the instance.
    // You may also want to append '-impl/-service' with a specific identifier like
    // '-vendor' or '-<hardware identifier>' etc to distinguish it.
    //name: "android.hardware.hello@1.0-impl",                                       --> comment here
    relative_install_path: "hw",
    // FIXME: this should be 'vendor: true' for modules that will eventually be
    // on AOSP.
    proprietary: true,
    name: "android.hardware.hello@1.0-service",				#	--> add here
    srcs: [
        "Hello.cpp",
        "service.cpp",							#	--> add service.cpp
    ],
    shared_libs: [
        "libhidlbase",
        "libhidltransport",
        "libutils",
        "android.hardware.hello@1.0",
    ],
}

