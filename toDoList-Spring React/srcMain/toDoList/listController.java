package toDoList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
public class listController {

    @Autowired
    private listRepository repository;

    @Autowired
    private  itemRepository itemRepository;

    @PostMapping("/lists")
    public ResponseEntity<listResponse> create(@RequestBody listRequest todoListRequest) {
        list todoList = repository.save(list.from(todoListRequest));
        return new ResponseEntity<>(listResponse.from(todoList),HttpStatus.CREATED);
    }

    @PostMapping("/lists/{id}/items")
    public ResponseEntity<itemResponse> createItem(@PathVariable("id") Long id, @RequestBody itemRequest todoItemRequest,@RequestBody listRequest todoListRequest ) {
    	list todoList = repository.save(list.from(todoListRequest));
    	todoList = repository.findOneByIdAndOwner(id, todoList);
        item todoItem = itemRepository.save(item.from(todoItemRequest, todoList));
        return new ResponseEntity<>(itemResponse.from(todoItem),HttpStatus.CREATED);
    }
    @GetMapping("/lists/{id}")
    public ResponseEntity<list> get(@PathVariable("id") Long id,@RequestBody listRequest todoListRequest) {
    	list todoList = repository.save(list.from(todoListRequest));
    	todoList = repository.findOneByIdAndOwner(id, todoList);
        return new ResponseEntity<>(repository.findOneByIdAndOwner(id,todoList), HttpStatus.OK);
    }
    @GetMapping("/items/{itemId}")
    public ResponseEntity<item> get(@PathVariable("id") Long id,@PathVariable("itemId") Long itemId,@RequestBody listRequest todoListRequest) {
    	list todoList = repository.save(list.from(todoListRequest));
    	todoList = repository.findOneByIdAndOwner(id, todoList);
    	return new ResponseEntity<>(itemRepository.findOneByIdAndList(itemId, todoList), HttpStatus.OK);
    }

    @DeleteMapping("/lists/{id}")
    public ResponseEntity<String> delete(@PathVariable("id") Long id,
    		@RequestBody listRequest todoListRequest) {
    	list todoList = repository.save(list.from(todoListRequest));
        repository.deleteByIdAndOwner(id, todoList);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    @DeleteMapping("/lists/{id}/items/{itemId}")
    public ResponseEntity<String> delete(@PathVariable("id") Long id,
                                         @PathVariable("itemId") Long itemId,
                                         @RequestBody listRequest todoListRequest) {
    	list todoList = repository.save(list.from(todoListRequest));
        todoList = repository.findOneByIdAndOwner(id, todoList);
        itemRepository.deleteByIdAndList(itemId, todoList);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

  


}