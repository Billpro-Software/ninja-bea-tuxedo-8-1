#!/bin/sh
# Recommended arguments to Quickstart are
# install.dir="product-install-dir"
# product.alias.id="product-alias-id"
# product.alias.version="product-alias-version"

# Set JAVA Home
JAVA_HOME="C:/bea/jdeveloper/jdk160_21"

# Set BEA Home
BEAHOME="C:/bea/jdeveloper"

cd "${BEAHOME}/utils/quickstart"

"${JAVA_HOME}/bin/java" ${JAVA_VM} -Djava.library.path="${BEAHOME}/utils/uninstall" -jar "${BEAHOME}/utils/quickstart/quickstart.jar" $*


exit $?
