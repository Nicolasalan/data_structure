DOCKER_VOLUMES = \
	--volume="$(shell pwd)":"/ws":rw 

.PHONY: -les
-les:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && gcc insertion.c -o insertion && ./insertion"