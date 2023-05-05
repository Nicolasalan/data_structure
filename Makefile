DOCKER_VOLUMES = \
	--volume="$(shell pwd)":"/ws":rw 

.PHONY: insert
insert:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && gcc insertion.c -o insertion && ./insertion"

.PHONY: clear
clear:
	@echo "Clearing..."
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && rm insertion"

