package toDoList;

import java.util.Date;

import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@NoArgsConstructor
public class itemResponse {
    private long id;
    private String name;
    private String decription;
    private Date deadline;
    private boolean completed;
    
    public itemResponse(long id, String name,String description,Date deadline) {
        this.setId(id);
        this.setName(name);
        this.setDecription(description);
        this.setDeadline(deadline);
    }

    public static itemResponse from(item todoItem) {
        return new itemResponse(todoItem.getId(), todoItem.getName(),todoItem.getDescription(),todoItem.getDate());
    }

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDecription() {
		return decription;
	}

	public void setDecription(String decription) {
		this.decription = decription;
	}

	public Date getDeadline() {
		return deadline;
	}

	public void setDeadline(Date deadline) {
		this.deadline = deadline;
	}

	public boolean isCompleted() {
		return completed;
	}

	public void setCompleted(boolean completed) {
		this.completed = completed;
	}
}