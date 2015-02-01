<?php

/**
 * @file
 * Element controller class.
 */

/**
 * The Controller for Element entities.
 */
class ElementController extends EntityAPIController {
  /**
   * Create a Element.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our entity.
    $values += array(
      'element_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
