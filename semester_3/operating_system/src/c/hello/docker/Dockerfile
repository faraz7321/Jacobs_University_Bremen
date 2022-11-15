# compile static binary:
#       gcc -static -o hello hello.c
#
# create image:
#       sudo docker build -t moin .
#
# run image:
#       sudo docker run moin
#
# to get a minimal shell:
#       sudo docker run -it --rm busybox
#
#	docker exec -it $CONTAINER /bin/sh

# Q: Why is it necessary to compile a static hello?

##FROM scratch
FROM busybox
#CMD ["sh"]
COPY hello /
CMD ["/hello"]
