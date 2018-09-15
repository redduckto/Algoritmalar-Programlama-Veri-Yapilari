package toDoList;

import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@NoArgsConstructor
public class listRequest {

    private String name;

    public listRequest(String name) {
        this.name = name;
    }

	public String getName() {
		return name;
	}

}