package test;

import io.restassured.RestAssured;
import io.restassured.http.ContentType;
import toDoList.itemRequest;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.context.embedded.LocalServerPort;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;


import static io.restassured.RestAssured.given;
import static org.hamcrest.core.IsEqual.equalTo;

@RunWith(SpringRunner.class)
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class testOutput {

	@LocalServerPort
	private int serverPort;

	@Before
	public void settin() {
		RestAssured.baseURI = "http://localhost";
		RestAssured.port = serverPort;
	}

	@Test
	public void listItemIsCreated() {
		itemRequest request = new itemRequest("write a component test");

		given()
	            .body(request)
				.accept(ContentType.JSON)
				.contentType(ContentType.JSON)
				.post("/lists/1/items")
				.then()
				.statusCode(201)
				.body("id", equalTo("7"))
				.body("name", equalTo("write a component test"));
	}

}
