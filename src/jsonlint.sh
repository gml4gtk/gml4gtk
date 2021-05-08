#!/bin/sh -x
if [ ! -f "./jsonlint" ]; then
  make jsonlint
fi
./jsonlint --verify t.jgf
./jsonlint --tree t.jgf
exit 0
See: ../data/json-graph-schema_v2.json

