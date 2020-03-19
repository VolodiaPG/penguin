#!/bin/bash

cp -r /home/develop/cache/node_modules/. ./www/node_modules
cd www/
exec npm i