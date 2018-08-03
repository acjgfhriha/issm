#!/bin/bash
set -eu

#Some cleanup
rm -rf ec2-api-tools.zip
rm -rf ec2-api-tools-1.6.3.1

#Download from ISSM server
$ISSM_DIR/scripts/DownloadExternalPackage.py 'http://issm.jpl.nasa.gov/files/externalpackages/ec2-api-tools.zip' 'ec2-api-tools.zip'
$ISSM_DIR/scripts/DownloadExternalPackage.py 'http://issm.jpl.nasa.gov/files/externalpackages/docs/ec2-ug.pdf' 'ec2-ug.pdf'

#Untar 
unzip ec2-api-tools.zip
