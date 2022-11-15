IMAGE = moin

hello:
	gcc -static -o hello -Wall -O2 hello.c

create-image:
	docker image build -t $(IMAGE) .

delete-image:
	docker image rm $(IMAGE)

run-image:
	docker run --rm $(IMAGE)

run-shell:
	docker run -it --rm busybox

clean:
	rm -f hello *~
