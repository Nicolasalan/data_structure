DOCKER_VOLUMES = \
	--volume="$(shell pwd)":"/ws":rw 

# === Insert ===
.PHONY: insert
insert:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LES && gcc insertion.c -o insertion && ./insertion"

# === Linked ===
.PHONY: linked
linked:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LEE && gcc linkedlist.c -o linkedlist && ./linkedlist"

# === Doubly ===
.PHONY: doubly
doubly:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LDDE && gcc doubly.c -o doubly && ./doubly"

# === Manager ===
.PHONY: manager
manager:
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd project && gcc manager.c -o manager && ./manager"

# ==================== CLEAR ====================

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

# === Clear Doubly ===
.PHONY: clear-doubly
clear-doubly:
	@echo "Clearing..."
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd LDDE && rm doubly"

# === Clear Manager ===
.PHONY: clear-manager
clear-manager:
	@echo "Clearing..."
	@docker run -it ${DOCKER_VOLUMES} data bash -c "cd project && rm manager"