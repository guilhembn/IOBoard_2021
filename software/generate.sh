#!/bin/bash
mkdir -p include/generated
cd lib/EmbeddedProto
protoc --plugin=protoc-gen-eams=protoc-gen-eams -I../../protoduck --eams_out=../../include/generated ../../protoduck/*.proto

