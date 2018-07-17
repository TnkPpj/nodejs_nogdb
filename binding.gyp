{
    "targets": [
        {
            "target_name": "nogdb_js",
            "cflags_cc": [
                "-std=c++11",
                "-Wall"
            ],
            "sources": [
                "src/init_module.cc",
                "src/context.cc",
                "src/txn.cc",
                "src/class.cc"
            ],
            "include_dirs": [
                "src",
                "/usr/local/incude",
                "<!(node -e \"require('nan')\")"
            ],
            "libraries": [
                "-lnogdb",
		"-latomic"
            ]

        }
    ]
}
