package toDoList;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import java.util.Date;
import javax.persistence.*;



@Entity
@Data
@NoArgsConstructor
@ToString(exclude = {"list"})
@Table(name="todo_item")
public class item {
  //  @Id
  //  @GeneratedValue
    private Long id;
    private String name;
    private String description;
    private Date deadline;
    private boolean completed;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "TODO_LIST_ID")
    @JsonIgnore
   
	private list liste;


    public item(String name, list liste) {
        this.name = name;
        this.liste = liste;
    }

    public static item from(itemRequest todoItemRequest, list todoList) {
        return new item(todoItemRequest.getName(), todoList);
    }

    public void merge(itemRequest request) {
        this.name = request.getName();
        this.setCompleted(request.isCompleted());
    }

	public String getName() {
		// TODO Auto-generated method stub
		return name;
	}

	public long getId() {
		// TODO Auto-generated method stub
		return id;
	}
	public String getDescription() {
		// TODO Auto-generated method stub
		return description;
	}

	public Date getDate() {
		// TODO Auto-generated method stub
		return deadline;
	}

	public boolean isCompleted() {
		return completed;
	}

	public void setCompleted(boolean completed) {
		this.completed = completed;
	}
}