#!/bin/bash
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

echo $BUILD_BUILDURI
$BUILD_SOURCESDIRECTORY/tools/ci_build/github/windows/post_code_coverage_to_dashboard.py --commit_hash=$BUILD_SOURCEVERSION --report_file="$BUILD_BINARIESDIRECTORY/report.json" --report_url="https://aiinfra.visualstudio.com/Lotus/_build/results?buildId=$BUILD_BUILDID" --branch $BUILD_SOURCEBRANCHNAME --arch $AGENT_OSARCHITECTURE --os $AGENT_OS --build_config default