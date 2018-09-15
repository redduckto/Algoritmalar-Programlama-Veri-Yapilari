import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import { ListGroup } from 'react-bootstrap';
import { ListGroupItem } from 'react-bootstrap';
import { FormControl } from 'react-bootstrap';
import { FormGroup } from 'react-bootstrap';
import { ControlLabel } from 'react-bootstrap';
import { Button } from 'react-bootstrap';
import { InputGroup } from 'react-bootstrap';
import items from '/items';


class App extends Component {

    constructor(props) {
        super(props);
        this.state = {todoLists: [], newListName: '', todoItemAdders: [],newItemName: '',newItemDesc : '', newItemDeadline: '', newItemStatus : '',updatedObjName : ''};
        this.handleNewListNameChange = this.handleNewListNameChange.bind(this);
        this.handleItemAdderNameChange = this.handleItemAdderNameChange.bind(this);
        this.handleNewList = this.handleNewList.bind(this);
        this.handleDeleteList = this.handleDeleteList.bind(this);
        this.handleNewItem = this.handleNewItem.bind(this);
        this.handleOrderItem = this.handleOrderItem.bind(this);
    }

    componentDidMount() {
        fetch('/lists', {
            method: 'GET',
            credentials: 'same-origin'
        }).then(response => {
            return response.json();

        }).then(json => {
            this.setState({todoLists: json, todoItemAdders: new Array(json.length).fill('')});
        });
    }

    handleItemAdderNameChange(index, name) {
        this.setState(function (prevState) {
            let myTodoItemAdders = prevState.todoItemAdders;
            myTodoItemAdders[index] = name;
            return {
                todoItemAdders: myTodoItemAdders
            };
        });
    }

    handleNewListNameChange(listName) {
        this.setState({newListName: listName});
    }


    handleNewList() {
        let newList = {
            name: this.state.newListName
        };
        fetch('/lists', {
            method: 'POST',
            credentials: 'same-origin',
            body: JSON.stringify(newList),
            headers: new Headers({
                'Content-Type': 'application/json'
            })
        }).then(response => {
            return response.json();
        }).then(json => {
            this.setState(function (prevState) {
                let myTodoLists = prevState.todoLists;
                myTodoLists.push(json);
                return {
                    todoLists: myTodoLists,
                    newListName: ''
                };
            });
        });
    }
    

    handleNewItem(index, listId) {
        let newItem = {
            name: this.state.todoItemAdders[index]
        }
        fetch('/lists/' + listId + '/items', {
            method: 'POST',
            credentials: 'same-origin',
            body: JSON.stringify(newItem),
            headers: new Headers({
                'Content-Type': 'application/json'
            })
        }).then(response => {
            return response.json();
        }).then(json => {
            this.setState(function (prevState) {
                let myTodoLists = prevState.todoLists;
                myTodoLists.forEach(function (todoList) {
                    if (todoList.id == listId) {
                        todoList.items.push(json);
                    }
                });
                let myTodoItemAdders = prevState.todoItemAdders;
                myTodoItemAdders[index] = '';
                return {
                    todoLists: myTodoLists,
                    todoItemAdders: myTodoItemAdders
                };
            });
        });
    }


    handleDeleteList(listId) {
        fetch('/lists/' + listId, {
            method: 'DELETE',
            credentials: 'same-origin'
        }).then(response => {
            this.setState(function (prevState) {
                let myTodoLists = prevState.todoLists.filter((todoList =>
                    todoList.id !== listId
                ));
                return {
                    todoLists: myTodoLists
                };
            });
        });
    }
    
     handleDeleteItem(listId, itemId) {
        fetch('/lists/' + listId + '/items/' + itemId, {
            method: 'DELETE',
            credentials: 'same-origin'
        }).then(response => {
            this.setState(function (prevState) {
                let myItems = prevState.items.filter(item => item.id !== itemId);
                return {
                    items: myItems
                };
            });
        })
    }
 /*   handleOrderItem()
    {
        
         fetch('/items', {
           method: 'GET',
            credentials: 'same-origin'
        }).then(response => {
            return response.json();
        }).then(json => {
            his.setState(function (prevState, props) {
                let myTodoItem = prevState.items;
                myTodoItem.forEach(function (items) {
                    if (items.id!= '' ) {
                        return {
                    items: myTodoItem,

                };
                    }
                });
               
            });
        });

    }*/
 

    render() {
        const newListName = this.state.newListName;
        const newItemName = this.state.newItemName;

        return (
            <div>
                <AddTodoList listName={newListName}
                             onAddList={this.handleNewList}
                             onListNameChange={this.handleNewListNameChange}/>
                <AddTodoItem itemName={newItemName}
                             onAddItem={this.handleNewItem}/>
                <OrderItem   object = {items}/>
                <ListGroupItem key={items.id}>
                        <DeleteObject object={items}
                             onDeleteObject={(itemId) => this.handleDeleteItem(itemId)}/>
                        <DeleteObject object={lists}
                             onDeleteObject={(listId) => this.handleDeleteList(listId)}/>
                             
                    </ListGroupItem>
            </div>
        );
    }

}
class OrderItem extends Component {

  state = {
    items,
    itemName: [],
    itemDesc: [],
    itemDeadline: [],
  }

  componentDidMount() {
    const { items, itemName,itemDesc,itemDeadline} = this.state;

    itemName = items.map(i => i.name);
    itemDesc = items.map(i => i.description);
    itemDeadline = items.map(i => i.deadline);

    this.setState({ itemName },{itemDesc},{itemDeadline})
  }

  sortAscending = () => {
    const { itemName,itemDesc,itemDeadline } = this.state;
    itemName.sort((a, b) => a - b)    
    itemDesc.sort((a, b) => a - b) 
    itemDeadline.sort((a, b) => a - b) 
    this.setState({ itemName },{itemDesc},{itemDeadline})
  }

  render() {
    const { itemName,itemDesc,itemDeadline} = this.state;
    return (
      <div>
        <ul>
          {
            itemName.map((i, o) => {
              return <li>{o} -{i}</li>;
            })
          }
        </ul>
        <button onClick={this.sortAscending}>order by name</button>
        <ul>
          {
            itemDesc.map((i, o) => {
              return <li>{o} -{i}</li>;
            })
          }
        </ul>
        <button onClick={this.sortAscending}>order by description</button>
        <ul>
          {
            itemDeadline.map((i, o) => {
              return <li>{o} -{i}</li>;
            })
          }
        </ul>
        <button onClick={this.sortAscending}>order by deadline</button>
      </div>
    );
  }
}
class DeleteObject extends React.Component {

    constructor(props) {
        super(props);

        this.handleSubmit = this.handleSubmit.bind(this);
        this.handleNameChange = this.handleNameChange.bind(this);
        this.handleDeleteButtonClick = this.handleDeleteButtonClick.bind(this);
    }

    handleSubmit(e, objId) {
        e.preventDefault();
        this.handleDeleteButtonClick(objId);
    }

    handleNameChange(e) {
        this.props.onNameChange(e.target.value);
    }

    handleDeleteButtonClick(objId) {
        this.props.onDeleteObject(objId);
    }

    render() {
        let obj = this.props.object;
        return (
            <form onSubmit={(e) => this.handleSubmit(e, obj.id)}>
                <FormGroup>
                    <InputGroup>
                        <FormControl
                            type="text"
                            placeholder="Enter text"
                            value={this.props.onNameChange}
                            onChange={this.handleNameChange}
                        />
                        <InputGroup.Button>
                            <Button onClick={() => this.handleDeleteButtonClick(obj.id)}>Delete Item</Button>
                        </InputGroup.Button>
                        <InputGroup.Button>
                            <Button bsStyle="danger"
                                    onClick={() => this.handleDeleteButtonClick(obj.id)}>Delete List</Button>
                        </InputGroup.Button>
                    </InputGroup>
                </FormGroup>
            </form>
        );
    }

}



class AddTodoList extends Component {
    constructor(props) {
        super(props);
        
        this.handleChange = this.handleChange.bind(this);
        this.handleClick = this.handleClick.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }
    
    handleChange(e) {
        this.props.onListNameChange(e.target.value);
    }

    handleClick() {
        this.props.onAddList();
    }

    handleSubmit(e) {
        e.preventDefault();
        this.handleClick();
    }

    render() {
        const listName = this.props.listName;
        return (
            <form onSubmit={this.handleSubmit}>
                <FormGroup>
                    <ControlLabel>Enter a name for your new list:</ControlLabel>
                    <FormControl
                        type="text"
                        value={listName}
                        placeholder="Enter text"
                        onChange={this.handleChange}
                    />
                    <Button bsStyle="default" onClick={this.handleClick}>Add List</Button>
                </FormGroup>
            </form>
        );
    }
}

class AddTodoItem extends Component {
    constructor(props) {
        super(props);
         this.state = {
          newItemName: '',
          newItemDesc: '',
          newItemDeadline: '',
          newItemStatus: '',
        };
        this.handleClick = this.handleClick.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleClick() {
        this.props.onAddItem();
    }

    handleSubmit(e) {
        e.preventDefault();
        this.handleClick();
    }

    render() {
        const { newItemName, newItemDesc, newItemDeadline , newItemStatus } = this.state;
        return (
            <form onSubmit={this.handleSubmit}>
        <ListGroup>
             <input
              type="text"
              name="newItemName"
              value={newItemName}
              onChange={this.onChange}
            />
            <input
              type="text"
              name="newItemDesc"
              value={newItemDesc}
              onChange={this.onChange}
            />
            <input
              type="text"
              name="newItemDeadline"
              value={newItemDeadline}
              onChange={this.onChange}
            />
             <input
              type="text"
              name="newItemStatus"
              value={newItemStatus}
              onChange={this.onChange}
            />
            </ListGroup>
                    />
                    <Button bsStyle="default" onClick={this.handleClick}>Add Item</Button>
                
            </form>
        );
    }
}


ReactDOM.render(<App />, document.getElementById('root'));