#!/bin/bash

HEADER_FILE="src/include/version.h"
DOXYFILE="Doxyfile"

function show_help() {
    cat <<:EOF
Usage: ./tools/update-version.sh <semver-version>

Example: ./tools/update-version.sh 1.2.3
:EOF
}

function main() {
    local version="$1"

    if [ -z "$version" -o "$version" == "-h" -o "$version" == "--help" ]; then
        show_help
        exit 0
    fi

    if ! grep -qE "^[0-9]+\.[0-9]+\.[0-9]+$" <<< "$version"; then
        echo "Version '$version' has invalid format. Expected a semantic version tag." >&2
        exit 1
    fi

    update_version_file "$version"
    update_header "$version"
    update_doxyfile "$version"
}

function update_version_file() {
    local version="${1?}"

    echo "$version" > .version
}

function update_header() {
    local version="${1?}"

    sed -Ei "s/LIBMYA_VERSION\s+\"[^\"]+\"/LIBMYA_VERSION \"$version\"/" "$HEADER_FILE"
}

function update_doxyfile() {
    local version="${1?}"

    sed -Ei "s/(PROJECT_NUMBER\s+=\s+)\"[^\"]+\"/\\1\"$version\"/" "$DOXYFILE"
}


main "$@"
