#!/bin/sh

echo ${var:-"Apples"}
echo "I love ${var}"

echo ${var:="Oranges"}
echo "But i also love ${var}"

unset var
echo ${var:+"This is default value"}
echo "Healthiest fruit is $var"

echo ${var:?"Print this message"}
echo "I eat ${var}"

