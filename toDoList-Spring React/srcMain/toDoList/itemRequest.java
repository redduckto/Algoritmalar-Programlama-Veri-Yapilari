package toDoList;

import java.util.Date;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@NoArgsConstructor
@JsonIgnoreProperties(ignoreUnknown = true)
public class itemRequest {


    private String name;
    private String description;
    private Date deadline;
    private boolean completed;

    public itemRequest(String name) {
        this.name = name;
    }

	public String getName() {
		// TODO Auto-generated method stub
		return name;
	}

	public boolean isCompleted() {
		// TODO Auto-generated method stub
		return completed;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public Date getDeadline() {
		return deadline;
	}

	public void setDeadline(Date deadline) {
		this.deadline = deadline;
	}
}