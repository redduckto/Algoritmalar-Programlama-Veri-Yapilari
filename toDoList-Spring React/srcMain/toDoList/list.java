package toDoList;



import lombok.Data;
import lombok.NoArgsConstructor;
import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Data
@NoArgsConstructor
@Table(name="todo_list")
public class list {

    @Id
    @GeneratedValue
    private Long id;
    private String name;

    @OneToMany(mappedBy = "list",
            cascade = CascadeType.ALL,
            fetch = FetchType.LAZY)
    private List<item> items = new ArrayList<>();


    public list(String name) {
        this.name = name;
    }

    public static list from(listRequest todoListRequest) {
        return new list(todoListRequest.getName());
    }

    public void merge(listRequest request) {
        setName(request.getName());
    }

	private void setName(String name) {
		// TODO Auto-generated method stub
		this.name=name;
		
	}

	public long getId() {
		// TODO Auto-generated method stub
		return id;
	}

	public String getName() {
		// TODO Auto-generated method stub
		return name;
	}
}