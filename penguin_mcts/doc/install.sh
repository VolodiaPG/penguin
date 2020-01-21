location=$1   # the location of the root of the project
port="8080"

# from the root location of the project directory, get the named parameters
www="www/"
bin="bin/"
doc="doc/"
doxygen="doxygen/html/"


echo "Creating nginx.conf in $location/nginx.conf"
cat <<EOF  > "$location/nginx.conf"
events { }
http {
    # solve issues serving css, js and other files...
    include       /etc/nginx/mime.types;
    server {
        listen $port;
        server_name localhost;
        server_name 127.0.0.1;

        # default is the www folder

        location / {
            alias $location$www;
            autoindex on;
        }

        # serve the bin folder and subdirs
        location /bin {
            alias $location$bin;
            index main.html;
        }

        # serve the doxygen documentation, and subdirs
        location /doc {
            alias $location$doc$doxygen;
            autoindex on;
        }
    }
}
EOF