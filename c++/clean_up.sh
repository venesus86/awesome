#!/bin/sh
remove_list=`find -type f ! -path "*/.vscode/*" | grep -v "\.cpp\|\.sh\|\.h"`
if [ -z "$remove_list" ]; then
	echo "there is no remove_list"
	exit 0
fi

echo "remove list:"
echo "$remove_list"
echo "Remove? (Y/n)"
read answer
if [ -z "$answer" ] || [ "$answer" = "Y" ] || [ "$answer" = "y" ]; then
	echo "Remove them"
	rm -rf $remove_list
else
	echo "Do not remove them"
fi
