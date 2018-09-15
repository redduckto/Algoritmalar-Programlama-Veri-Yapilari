package toDoList;


import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;


@Data
@NoArgsConstructor
public class listResponse {
    private Long id;
    private String name;
    private List<item> items = new ArrayList<>();

    public listResponse(Long id, String name) {
        this.setId(id);
        this.setName(name);
    }

    public static listResponse from(list todoList) {
        return new listResponse(todoList.getId(), todoList.getName());
    }

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<item> getItems() {
		return items;
	}

	public void setItems(List<item> items) {
		this.items = items;
	}
}