package toDoList;


import org.springframework.data.repository.CrudRepository;

import javax.transaction.Transactional;


public interface itemRepository extends CrudRepository<item, Long> {
    item findOneByIdAndList(Long id, list todoList);

    @Transactional
    void deleteByIdAndList(Long id, list todoList);
}