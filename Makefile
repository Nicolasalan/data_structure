DOCKER_VOLUMES = \
	--volume="$(shell pwd)":"/ws":rw 

# === Insert ===
.PHONY: insert
insert:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && gcc insertion.c -o insertion && ./insertion"

# === Insert ===
.PHONY: linked
linked:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LEE && gcc linkedlist.c -o linkedlist && ./linkedlist"

# === Clear Insert ===
.PHONY: clear-insert
clear-insert:
	@echo "Clearing..."
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && rm insertion"

# === Clear Linked ===
.PHONY: clear-linked
clear-linked:
	@echo "Clearing..."
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LEE && rm linkedlist"