{
	"targets": [{
		"target_name": "memfd-create",
		"sources": [ "memfd-create.cc" ],
		"include_dirs": [
			"<!(node -e \"require('nan')\")"
		],
		"cflags_cc": [
			"-std=c++11"
		],
		"conditions": [
			[ 'OS=="mac"',
				{ "xcode_settings": {
					'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
					'OTHER_LDFLAGS': ['-stdlib=libc++'],
					'MACOSX_DEPLOYMENT_TARGET': '10.8'
				}}
			]
		]
	}]
}
