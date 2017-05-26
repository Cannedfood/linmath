#!/bin/bash

scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

[ ! -d "${scriptdir}/include/xmath/" ] && mkdir "${scriptdir}/include/xmath/"

rm "${scriptdir}/include/xmath/"*

for header in "${scriptdir}/include/stx/math/"*
do
	if [ ! -d "${header}" ]
	then
		name=`basename ${header%.*}`
		printf '#include "%s"' "../stx/math/${name}.hpp" > "${scriptdir}/include/xmath/${name}"
	fi
done
